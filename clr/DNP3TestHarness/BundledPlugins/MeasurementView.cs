﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace Automatak.DNP3.Simulator
{
    public partial class MeasurementView : UserControl, IMeasurementObserver
    {
        MeasurementCollection collection = new MeasurementCollection();
        SortedDictionary<ushort, int> indexToRow = new SortedDictionary<ushort, int>();

        public MeasurementView()
        {
            InitializeComponent();           
        }

        void BindCollection(MeasurementCollection measurements)
        {
            if (collection != null)
            {
                collection.RemoveObserver(this);
            }
        }

        ListViewItem CreateItem(Measurement m)
        {
            string[] text = { m.Index.ToString(), m.Value, m.Flags, m.Timestamp.ToString() };
            var item = new ListViewItem(text);
            return item;
        }

        void RefreshAllRows(IEnumerable<Measurement> rows)
        {
            try
            {
                this.listView.BeginUpdate();
                this.listView.Items.Clear();
                this.indexToRow.Clear();
                int ri = 0;
                foreach (var m in rows)
                {
                    this.listView.Items.Add(CreateItem(m));
                    indexToRow[m.Index] = ri;
                    ++ri;
                }
            }
            finally
            {
                this.listView.EndUpdate();
            }
        }

        void InsertOrUpdate(Measurement meas)
        {
            if (indexToRow.ContainsKey(meas.Index))
            {
                var row = indexToRow[meas.Index];
                this.listView.Items[row] = CreateItem(meas);
            }
            else
            { 
                // figure out where to insert
                var entry = indexToRow.FirstOrDefault(kvp => kvp.Key > meas.Index);
                if (entry.Equals(default(KeyValuePair<ushort, int>)))
                {
                    var row = listView.Items.Count;
                    listView.Items.Add(CreateItem(meas));
                    indexToRow[meas.Index] = row;
                }
                else
                {
                    listView.Items.Insert(entry.Value, CreateItem(meas));
                    indexToRow[meas.Index] = entry.Value;
                    var rows = indexToRow.Select(kvp => kvp.Key > meas.Index);
                    foreach (var kvp in indexToRow)
                    {
                        if (kvp.Key > meas.Index)
                        {
                            indexToRow[kvp.Key] = kvp.Value + 1;                            
                        }
                    }
                }
            }
        }

        void IMeasurementObserver.Refresh(IEnumerable<Measurement> rows)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action(() => RefreshAllRows(rows)));
            }
            else
            {
                RefreshAllRows(rows);
            }
        }

        void IMeasurementObserver.Update(Measurement meas)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action(() => InsertOrUpdate(meas)));
            }
            else
            {
                this.InsertOrUpdate(meas);
            }
        }

        private void listView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            if (e.IsSelected)
            {
                e.Item.Selected = false;
            }
        }
    }
}
